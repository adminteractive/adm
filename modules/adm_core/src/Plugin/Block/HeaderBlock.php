<?php

namespace Drupal\adm_core\Plugin\Block;

use Drupal\Core\Block\BlockBase;
use Drupal\Core\Cache\Cache;
use Drupal\Core\Config\ConfigFactoryInterface;
use Drupal\Core\Entity\EntityTypeManagerInterface;
use Drupal\Core\Language\LanguageInterface;
use Drupal\Core\Language\LanguageManagerInterface;
use Drupal\Core\Menu\MenuLinkTreeInterface;
use Drupal\Core\Menu\MenuTreeParameters;
use Drupal\Core\Path\PathMatcherInterface;
use Drupal\Core\Plugin\ContainerFactoryPluginInterface;
use Drupal\Core\Routing\RouteMatchInterface;
use Drupal\Core\Theme\ThemeInitializationInterface;
use Drupal\Core\Theme\ThemeManagerInterface;
use Drupal\Core\Url;
use Symfony\Component\DependencyInjection\ContainerInterface;

/**
 * Provides a 'Header' block.
 *
 * @Block(
 *   id = "adm_header_block",
 *   admin_label = @Translation("Header block")
 * )
 */
class HeaderBlock extends BlockBase implements ContainerFactoryPluginInterface {

  /**
   * The language manager.
   *
   * @var \Drupal\Core\Language\LanguageManagerInterface
   */
  protected $languageManager;

  /**
   * The path matcher.
   *
   * @var \Drupal\Core\Path\PathMatcherInterface
   */
  protected $pathMatcher;

  /**
   * Drupal\Core\Menu\MenuLinkTreeInterface definition.
   *
   * @var \Drupal\Core\Menu\MenuLinkTreeInterface
   */
  protected $menuLinkTree;

  /**
   * The config factory service.
   *
   * @var \Drupal\Core\Config\ConfigFactoryInterface
   */
  protected $configFactory;

  /**
   * The entity type manager service.
   *
   * @var \Drupal\Core\Entity\EntityTypeManagerInterface
   */
  protected $entityTypeManager;

  /**
   * The route match service.
   *
   * @var \Drupal\Core\Routing\RouteMatchInterface
   */
  protected $routeMatch;

  /**
   * The theme manager interface.
   *
   * @var \Drupal\Core\Theme\ThemeManagerInterface
   */
  protected $themeManager;

  /**
   * The theme initialization service.
   *
   * @var \Drupal\Core\Theme\ThemeInitializationInterface
   */
  protected $themeInitialization;

  /**
   * {@inheritdoc}
   */
  public function __construct(
    array $configuration,
    $plugin_id,
    $plugin_definition,
    LanguageManagerInterface $language_manager,
    PathMatcherInterface $path_matcher,
    MenuLinkTreeInterface $menuLinkTree,
    ConfigFactoryInterface $configFactory,
    EntityTypeManagerInterface $entity_type_manager,
    RouteMatchInterface $route_match,
    ThemeManagerInterface $theme_manager,
    ThemeInitializationInterface $theme_initialization
  ) {
    parent::__construct($configuration, $plugin_id, $plugin_definition);
    $this->languageManager = $language_manager;
    $this->pathMatcher = $path_matcher;
    $this->menuLinkTree = $menuLinkTree;
    $this->configFactory = $configFactory;
    $this->entityTypeManager = $entity_type_manager;
    $this->routeMatch = $route_match;
    $this->themeManager = $theme_manager;
    $this->themeInitialization = $theme_initialization;
  }

  /**
   * {@inheritdoc}
   */
  public static function create(ContainerInterface $container, array $configuration, $plugin_id, $plugin_definition) {
    return new static(
      $configuration,
      $plugin_id,
      $plugin_definition,
      $container->get('language_manager'),
      $container->get('path.matcher'),
      $container->get('menu.link_tree'),
      $container->get('config.factory'),
      $container->get('entity_type.manager'),
      $container->get('current_route_match'),
      $container->get('theme.manager'),
      $container->get('theme.initialization')
    );
  }

  /**
   * {@inheritdoc}
   */
  public function build() {
    $langcode = $this->languageManager->getCurrentLanguage()->getId();

    $build = [
      '#theme' => 'adm_header',
      '#cache' => [
        'tags' => [],
        'contexts' => [],
      ],
    ];

    $route_name = $this->pathMatcher->isFrontPage() ? '<front>' : '<current>';
    $type = 'language_interface';
    $links = $this->languageManager->getLanguageSwitchLinks($type, Url::fromRoute($route_name));

    if (isset($links->links)) {
      /** @var \Drupal\node\Entity\Node $node */
      $node = $this->routeMatch->getParameter('node');
      // Revision pages have node as a numeric string.
      if (is_numeric($node)) {
        $node = $this->entityTypeManager->getStorage('node')->load($node);
        $build['#cache']['tags'] = Cache::mergeTags($build['#cache']['tags'], $node->getCacheTags());
        $build['#cache']['contexts'] = Cache::mergeTags($build['#cache']['contexts'], $node->getCacheContexts());
      }

      foreach ($links->links as $key => $link) {
        // Change language titles to short ones.
        $links->links[$key]['title'] = _adm_core_language_short_name($key);

        // If node page and there isn't translation available,
        // change url to front.
        if ($node && !$node->hasTranslation($key)) {
          $neutral_languages = [
            LanguageInterface::LANGCODE_NOT_SPECIFIED,
            LanguageInterface::LANGCODE_NOT_APPLICABLE,
          ];
          $node_lang = $node->language()->getId();
          if (!in_array($node_lang, $neutral_languages, TRUE)) {
            $links->links[$key]['url'] = Url::fromRoute('<front>');
          }
        }

        if ($langcode === $key) {
          $links->links[$key]['active'] = TRUE;
        }
        else {
          $links->links[$key]['active'] = FALSE;
        }

        // Reset pager.
        if (isset($link['query']['page'])) {
          unset($links->links[$key]['query']['page']);
        }

        $links->links[$key]['attributes']['class'][] = 'nav-link';
      }

      $build['#link_switcher'] = [
        '#theme' => 'links__language_block',
        '#links' => $links->links,
        '#set_active_class' => TRUE,
      ];
    }

    $menus = _adm_menu_mapping('main');
    $menu_name = $menus[$langcode];
    $parameters = new MenuTreeParameters();
    $tree = $this->menuLinkTree->load($menu_name, $parameters);
    $manipulators = [
      ['callable' => 'menu.default_tree_manipulators:checkAccess'],
      ['callable' => 'menu.default_tree_manipulators:generateIndexAndSort'],
    ];
    $tree = $this->menuLinkTree->transform($tree, $manipulators);
    $menuBuild = $this->menuLinkTree->build($tree);
    if (empty($menuBuild['#cache']['tags'])) {
      $menuBuild['#cache']['tags'] = ['config:system.menu.' . $menu_name];
    }
    $build['#main_menu'] = $menuBuild;
    // We use menu per language strategy, to theme this,
    // we need to remove language code from theme suggestion.
    $build['#main_menu']['#theme'] = 'menu__main_menu';


    $theme = $this->themeManager->getActiveTheme()->getName();
    $theme_config = $this->configFactory->get('system.theme.' . $theme);
    $build['#cache']['tags'] = Cache::mergeTags($build['#cache']['tags'], $theme_config->getCacheTags());

    // Generate the path to the logo image.
    if ($theme_config->get('logo.' . $langcode . '.use_default')) {
      $logo = $this->themeInitialization
        ->getActiveThemeByName($theme)
        ->getLogo();
      $build['#logo'] = file_url_transform_relative(file_create_url($logo));
    }
    elseif ($logo_path = $theme_config->get('logo.' . $langcode . '.path')) {
      $build['#logo'] = file_url_transform_relative(file_create_url($logo_path));
    }

    return $build;
  }

}