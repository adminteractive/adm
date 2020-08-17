<?php
/**
 * @file
 * Enables modules and site configuration for a standard site installation.
 */

/**
 * Implements hook_install_tasks().
 *
 * @param $install_state
 *
 * @return array
 */
function adm_install_tasks(&$install_state) {
  $tasks = [];

/*  $tasks['\Drupal\adm\Form\AdmConfigurationsForm'] = [
    'display_name' => t('Additional configurations'),
    'type' => 'form',
  ];*/

  return $tasks;
}
