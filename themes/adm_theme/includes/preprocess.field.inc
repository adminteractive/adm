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
