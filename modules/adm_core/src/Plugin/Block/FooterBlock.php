<?php

namespace Drupal\adm_core\Plugin\Block;

use Drupal\Core\Block\BlockBase;
use Drupal\Core\Cache\Cache;
use Drupal\Core\Config\ConfigFactoryInterface;
use Drupal\Core\Form\FormBuilder;
use Drupal\Core\Language\LanguageManagerInterface;
use Drupal\Core\Menu\MenuLinkTreeInterface;
use Drupal\Core\Path\PathMatcherInterface;
use Drupal\Core\Plugin\ContainerFactoryPluginInterface;
use Drupal\Core\Url;
use Symfony\Component\DependencyInjection\ContainerInterface;

/**
 * Provides a 'Footer' block.
 *
 * @Block(
 *   id = "footer_block",
 *   admin_label = @Translation("Footer block")
 * )
 */
class FooterBlock extends BlockBase implements ContainerFactoryPluginInterface {

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
   * @var \Drupal\Core\Config\ConfigFactoryInterface
   */
  protected $configFactory;

  /**
   * The form builder.
   *
   * @var \Drupal\Core\Form\FormBuilder
   */
  protected $formBuilder;

  /**
   * {@inheritdoc}
   */
  public function __construct(array $configuration, $plugin_id, $plugin_definition, LanguageManagerInterface $language_manager, PathMatcherInterface $path_matcher, MenuLinkTreeInterface $menuLinkTree, ConfigFactoryInterface $configFactory, FormBuilder $formBuilder) {
    parent::__construct($configuration, $plugin_id, $plugin_definition);
    $this->languageManager = $language_manager;
    $this->pathMatcher = $path_matcher;
    $this->menuLinkTree = $menuLinkTree;
    $this->configFactory = $configFactory;
    $this->formBuilder = $formBuilder;
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
      $container->get('form_builder')
    );
  }

  /**
   * {@inheritdoc}
   */
  public function build() {
    $config = $this->configFactory->get('adm_core.footer_settings');
    $footer_content = $config->get('footer_content');
    $social_types = _adm_core_social_media_types();

    $build = [
      '#theme' => 'adm_footer',
    ];

    foreach ($footer_content as $item) {
      $build['items'][] = [
        'title' => [
          '#markup' => $item['column_title'],
        ],
        'content' => [
          '#type' => 'processed_text',
          '#text' => $item['column_content']['value'],
          '#format' => $item['column_content']['format'],
        ],
      ];
    }

    foreach ($config->get('social_icons') as $icon) {
      if (empty($icon['url'])) {
        $build['icons'][$icon['type']] = NULL;
      }
      else {
        $build['icons'][$icon['type']] = [
          '#type' => 'link',
          '#title' => isset($social_types[$icon['type']]) ? $social_types[$icon['type']] : $icon['type'],
          '#url' => Url::fromUri($icon['url']),
        ];
      }
    }

    return $build;
  }

  /**
   * {@inheritdoc}
   */
  public function getCacheTags() {
    $config = $this->configFactory->get('adm_core.footer_settings');
    $tags = parent::getCacheTags();

    $tags = Cache::mergeTags($tags, $config->getCacheTags());

    return $tags;
  }

}
