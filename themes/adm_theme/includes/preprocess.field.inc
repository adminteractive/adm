<?php
/**
 * @file
 */

use Drupal\Component\Utility\Html;

/**
 * Implements hook_preprocess_HOOK().
 */
function adm_theme_preprocess_field__field_accordion_item(array &$variables) {
  foreach ($variables['items'] as $delta => &$item) {
    $id = Html::getUniqueId('accordion-item-' . $delta);
    $item['content']['#attributes']['id'] = $id;
  }
}

/**
 * Implements hook_preprocess_HOOK().
 */
function adm_theme_preprocess_field__field_accordion_item_title(array &$variables) {
  $variables['attributes']['class'][] = 'card-header';
  // @see adm_theme_preprocess_paragraph__accordion_item().
  if (!empty($variables['element']['#content_attributes'])) {
    $variables['content_attributes'] = array_merge($variables['content_attributes'], $variables['element']['#content_attributes']);
  }

  $variables['content_attributes']['class'][] = 'collapsed';
  $variables['content_attributes']['data-toggle'] = 'collapse';
  $variables['content_attributes']['aria-expanded'] = 'false';

}

/**
 * Implements hook_preprocess_HOOK().
 */
function adm_theme_preprocess_field__field_accordion_item_body(array &$variables) {
  $variables['attributes']['class'][] = 'collapse';
  // @see adm_theme_preprocess_paragraph__accordion_item().
  if (!empty($variables['element']['#content_attributes'])) {
    $variables['content_attributes'] = array_merge($variables['content_attributes'], $variables['element']['#content_attributes']);
  }

  $variables['content_attributes']['class'][] = 'card-body';
}

/**
 * Implements hook_preprocess_HOOK().
 */
function adm_theme_preprocess_field__field_carousel_item(array &$variables) {
  $variables['attributes']['class'][] = 'carousel-inner';

  foreach ($variables['items'] as $delta => &$item) {
    $item['attributes']->addClass('carousel-item');

    if ($delta === 0) {
      $item['attributes']->addClass('active');
    }
  }
}

/**
 * Implements hook_preprocess_HOOK().
 */
function adm_theme_preprocess_field__field_carousel_item_caption(array &$variables) {
  $variables['attributes']['class'][] = 'carousel-caption';
}

/**
 * Implements hook_preprocess_HOOK().
 */
function adm_theme_preprocess_field__field_documents_list_items(array &$variables) {
  $variables['attributes']['class'][] = 'list-group';

  foreach ($variables['items'] as $delta => &$item) {
    $item['attributes']->addClass('list-group-item');
  }
}

function adm_theme_preprocess_field__field_tab_item(array &$variables) {
  $variables['attributes']['class'][] = 'tab-content';

  $tabs = [
    '#theme' => 'links__tabs',
    '#attributes' => [
      'class' => ['nav', 'nav-tabs'],
    ],
    '#links' => [],
  ];

  foreach ($variables['items'] as $delta => &$item) {
    /** @var \Drupal\paragraphs\Entity\Paragraph $item_paragraph */
    $item_paragraph = $item['content']['#paragraph'];
    $item_title = $item_paragraph->get('field_tab_item_title')->value;
    $transliterated = \Drupal::transliteration()->transliterate($item_title);
    $element_id = Html::getUniqueId($transliterated);
    $url = \Drupal\Core\Url::fromUserInput('#' . $element_id);

    $link = [
      'title' => $item_title,
      'url' => $url,
      'attributes' => [
        'class' => ['nav-link'],
        'id' => 'tab-' . $element_id,
        'data-toggle' => 'tab',
        'role' => 'tab',
        'aria-selected' => 'false',
      ]
    ];

    if ($delta === 0) {
      $link['attributes']['class'][] = 'active';

      $item['attributes']->addClass(['active', 'show']);
    }

    $tabs['#links'][] = $link;

    $item['attributes']->setAttribute('id', $element_id);
    $item['attributes']->setAttribute('role', 'tabpanel');
    $item['attributes']->setAttribute('aria-labelledby', 'tab-' . $element_id);
    $item['attributes']->addClass(['tab-pane', 'fade']);

  }

  $variables['tabs'] = $tabs;
}

/**
 * Implements hook_preprocess_HOOK().
 */
function adm_theme_preprocess_field__field_gallery_items(array &$variables) {
  $variables['attributes']['class'][] = 'row';
  $variables['attributes']['class'][] = 'mt-4';
  $variables['attributes']['class'][] = 'photoswipe-gallery';

  foreach ($variables['items'] as &$item) {
    $item['attributes']->addClass('col-sm-6');
    $item['attributes']->addClass('col-md-6');
    $item['attributes']->addClass('col-lg-3');
    $item['attributes']->addClass('mb-3');
  }

}

/**
 * Implements hook_preprocess_HOOK().
 */
function adm_theme_preprocess_field__field_media_image(array &$variables) {
  // Move photoswipe gallery class few levels up.
  // @see adm_theme_preprocess_field__field_gallery_items().
  if (($key = array_search('photoswipe-gallery', $variables['attributes']['class'])) !== false) {
    unset($variables['attributes']['class'][$key]);
  }
}

/**
 * Implements hook_preprocess_HOOK().
 */
function adm_theme_preprocess_image(array &$variables) {
  $variables['attributes']['class'][] = 'img-fluid';
}
