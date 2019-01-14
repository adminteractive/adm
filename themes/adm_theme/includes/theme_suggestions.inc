<?php

/**
 * Implements hook_theme_suggestions_HOOK_alter().
 */
function adm_theme_theme_suggestions_page_alter(array &$suggestions, array $variables) {

  if ($node = \Drupal::routeMatch()->getParameter('node')) {
    // Revision pages have node as a numeric string.
    if (is_numeric($node)) {
      $node = \Drupal\node\Entity\Node::load($node);
    }
    $content_type = $node->bundle();
    $suggestions[] = 'page__node__' . $content_type;
  }

  $http_error_suggestions = [
    'system.401' => 'page__401',
    'system.403' => 'page__403',
    'system.404' => 'page__404',
  ];
  $route_name = \Drupal::routeMatch()->getRouteName();

  if (isset($http_error_suggestions[$route_name])) {
    $path_args = explode('/', trim(\Drupal::service('path.current')->getPath(), '/'));
    $suggestions = theme_get_suggestions($path_args, 'page');
    $suggestions[] = $http_error_suggestions[$route_name];
  }

  return $suggestions;
}

/**
 * Implements hook_theme_suggestions_HOOK_alter().
 */
function adm_theme_theme_suggestions_form_element_label_alter(array &$suggestions, array $variables) {
  if (isset($variables['element']['#input_type'])) {
    $suggestions[] = $variables['theme_hook_original'] . '__' . $variables['element']['#input_type'];
  }
}

/**
 * Implements hook_theme_suggestions_HOOK_alter().
 */
function adm_theme_theme_suggestions_form_element_alter(array &$suggestions, array $variables) {
  $element = $variables['element'];

  if (isset($element['#type'])) {
    $suggestions[] = $variables['theme_hook_original'] . '__' . $element['#type'];
  }

  if (isset($element['#array_parents'])) {
    $string = implode('_', $element['#array_parents']);
    $suggestions[] = 'form_element__' . $string;
  }

  if (isset($element['#form_id'])) {
    $suggestions[] = 'form_element__' . $element['#form_id'];
  }
}

/**
 * Implements hook_theme_suggestions_HOOK_alter().
 */
function adm_theme_theme_suggestions_image_formatter_alter(array &$suggestions, array $variables) {
  /** @var \Drupal\image\Plugin\Field\FieldType\ImageItem $item */
  $item = $variables['item'];

  if (!empty($item)) {
    $suggestions[] = $variables['theme_hook_original'] . '__' . $item->getFieldDefinition()->getName();
  }
}

/**
 * Implements hook_theme_suggestions_HOOK_alter().
 */
function adm_theme_theme_suggestions_container_alter(array &$suggestions, array $variables) {

  if (isset($variables['element']['#attributes']['class'])) {

    $class = $variables['element']['#attributes']['class'];

    if ((is_array($class) && in_array('container-inline', $class))
      || (is_string($class) && $class === 'container-inline')
    ) {
      $suggestions[] = $variables['theme_hook_original'] . '__inline';
    }

  }

}
