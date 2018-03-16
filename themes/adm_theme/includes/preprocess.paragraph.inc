<?php

use Drupal\Component\Utility\Html;


/**
 * Implements hook_preprocess_HOOK().
 */
function adm_theme_preprocess_paragraph__carousel(array &$variables) {
  /** @var \Drupal\paragraphs\Entity\Paragraph $paragraph */
  $paragraph = $variables['elements']['#paragraph'];
  $variables['attributes']['class'][] = 'carousel';
  $variables['attributes']['class'][] = 'slide';
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
      '#value' => 'sdsds',
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
