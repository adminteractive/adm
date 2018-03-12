<?php

/**
 * Implements hook_preprocess_HOOK().
 */
function adm_theme_preprocess_input(array &$variables) {

  if (isset($variables['element']['#type'])) {

    switch ($variables['element']['#type']) {
      case 'textfield':
      case 'password':
      case 'email':
      case 'number':
      case 'date':
      case 'search':
        $variables['attributes']['class'][] = 'form-control';
        break;
    }
  }
}


/**
 * Implements hook_preprocess_HOOK().
 */
function adm_theme_preprocess_input__submit(array &$variables) {
  $variables['attributes']['class'][] = 'btn';
  $variables['attributes']['class'][] = 'btn-primary';
}
