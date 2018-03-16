<?php

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

