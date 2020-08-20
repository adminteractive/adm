<?php

use Drupal\Component\Utility\Html;
use Drupal\Core\Render\Element;
use Drupal\Core\Template\Attribute;

/**
 * Implements hook_preprocess_HOOK().
 */
function adm_theme_preprocess_paragraph(array &$variables) {
  // Wrap paragraph into specialized container.
  if (!isset($variables['container_wrap'])) {
    // Sometimes we don't need wrapper, then we set it FALSE.
    // @see adm_theme_preprocess_paragraph__carousel().
    $variables['container_wrap'] = TRUE;
  }

  // Set default attributes.
  $default_attributes = [
    'class' => ['container', 'mb-5'],
  ];

  $variables['container_attributes'] = new Attribute($default_attributes);
}

/**
 * Implements hook_preprocess_HOOK().
 */
function adm_theme_preprocess_paragraph__accordion(array &$variables) {
  $id = Html::getUniqueId('accordion');
  $variables['attributes']['id'] = $id;
  $content = &$variables['content'];

  if (!empty($content['field_accordion_item'])) {
    foreach (Element::children($content['field_accordion_item']) as $delta) {
      $content['field_accordion_item'][$delta]['#attributes']['data-parent'] = $id;
    }
  }
}

/**
 * Implements hook_preprocess_HOOK().
 */
function adm_theme_preprocess_paragraph__accordion_item(array &$variables) {
  // We don't need wrapper, disable it.
  $variables['container_wrap'] = FALSE;
  $variables['attributes']['class'][] = 'card';

  if (!empty($variables['attributes']['id'])) {
    $parent_id = $variables['attributes']['data-parent'];

    $title_id = Html::getUniqueId($parent_id . '-title');
    $body_id = Html::getUniqueId($parent_id . '-body');
    $variables['content']['field_accordion_item_title']['#attributes']['id'] = $title_id;
    $variables['content']['field_accordion_item_title']['#content_attributes']['data-target'] = '#' . $body_id;
    $variables['content']['field_accordion_item_body']['#attributes']['id'] = $body_id;
    $variables['content']['field_accordion_item_body']['#content_attributes']['aria-labelledby'] = $title_id;
  }
}

/**
 * Implements hook_preprocess_HOOK().
 */
function adm_theme_preprocess_paragraph__carousel(array &$variables) {
  // We don't need wrapper, disable it.
  $variables['container_wrap'] = FALSE;

  /** @var \Drupal\paragraphs\Entity\Paragraph $paragraph */
  $paragraph = $variables['elements']['#paragraph'];
  $variables['attributes']['class'][] = 'carousel';
  $variables['attributes']['class'][] = 'slide';
  $variables['attributes']['class'][] = 'mb-5';
  $variables['attributes']['data-ride'][] = 'carousel';

  if (!isset($variables['attributes']['id'])) {
    $variables['attributes']['id'] = Html::getUniqueId('carousel');
  }

  $html_id = $variables['attributes']['id'];
  $items_count = $paragraph->get('field_carousel_item')->count();
  $indicator_items = [];

  for ($i = 0; $i < $items_count; $i++) {
    $indicator_items[] = [
      '#wrapper_attributes' => [
        'class' => $i === 0 ? ['active'] : [],
        'data-slide-to' => $i,
        'data-target' => '#' . $html_id,
      ],
      '#value' => '',
    ];
  }

  $indicators = [
    '#theme' => 'item_list',
    '#list_type' => 'ol',
    '#attributes' => [
      'class' => ['carousel-indicators'],
    ],
    '#items' => $indicator_items,
  ];

  array_unshift($variables['content'], $indicators);

  $arrows = [];

  $arrows['prev'] = [
    '#type' => 'html_tag',
    '#tag' => 'a',
    '#value' => '<span class="carousel-control-prev-icon" aria-hidden="true"></span>
    <span class="sr-only">' . t('Previous') . '</span>',
    '#attributes' => [
      'class' => ['carousel-control-prev'],
      'href' => '#' . $html_id,
      'role' => 'button',
      'data-slide' => 'prev',
    ]
  ];

  $arrows['next'] = $arrows['prev'];
  $arrows['next']['#attributes']['class'] = ['carousel-control-next'];
  $arrows['next']['#attributes']['data-slide'] = 'next';
  $arrows['next']['#value'] = '<span class="carousel-control-next-icon" aria-hidden="true"></span>
    <span class="sr-only">' . t('Next') . '</span>';

  $variables['content'][] = $arrows;
}

/**
 * Implements hook_preprocess_HOOK().
 */
function adm_theme_preprocess_paragraph__carousel_item(array &$variables) {
  // Disable container.
  $variables['container_wrap'] = FALSE;
}

/**
 * Implements hook_preprocess_HOOK().
 */
function adm_theme_preprocess_paragraph__tab_item(array &$variables) {
  // Disable container.
  $variables['container_wrap'] = FALSE;

  $variables['attributes']['class'][] = 'mt-3';
}
