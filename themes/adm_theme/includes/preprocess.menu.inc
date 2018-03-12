<?php

/**
 * Implements hook_preprocess_HOOK().
 */
function adm_theme_preprocess_menu__main(array &$variables) {
  $variables['attributes']['class'][] = 'navbar-nav';
  $variables['attributes']['class'][] = 'mr-auto';
}

/**
 * Implements hook_preprocess_HOOK().
 */
function adm_theme_preprocess_menu__account(array &$variables) {
  $variables['attributes']['class'][] = 'navbar-nav';
  $variables['attributes']['class'][] = 'mr-auto';
}
