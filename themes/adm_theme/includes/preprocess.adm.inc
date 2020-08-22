<?php

/**
 * @file
 */

use Drupal\Core\Render\Markup;

/**
 * Implements hook_preprocess_HOOK().
 */
function adm_theme_preprocess_adm_footer(&$variables) {
  $variables['attributes']['class'][] = 'pt-5';
  $variables['attributes']['class'][] = 'pb-5';

  $variables['social_icons'] = [
    '#theme' => 'links__footer_social_links',
    '#links' => [],
    '#attributes' => [
      'class' => ['list-group', 'list-group-horizontal-sm', 'list-social-vp'],
    ],
  ];

  $sprites = [
    'facebook' => 'fa-facebook',
    'twitter' => 'fa-twitter',
    'youtube' => 'fa-youtube',
    'rss' => 'fa-rss',
  ];

  foreach ($variables['content']['icons'] as $type => $link) {
    $variables['social_icons']['#links'][] = [
      'title' => Markup::create('<i class="fab ' . $sprites[$type] . '"></i>'),
      'url' => $link['#url'],
      'attributes' => [
        'class' => ['d-flex', 'align-items-center', 'justify-content-center'],
        'target' => '_blank',
      ],
    ];
  }
}

/**
 * Implements hook_preprocess_HOOK().
 */
function adm_theme_preprocess_links__footer_social_links(&$variables) {
  foreach ($variables['links'] as &$link) {
    $link['attributes']->addClass('list-group-item');
  }
}
