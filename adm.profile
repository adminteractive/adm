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

  $tasks['\Drupal\adm\Form\AdmConfigurationsForm'] = [
    'display_name' => t('Additional configurations'),
    'type' => 'form',
  ];

  $tasks['adm_batch_processing'] = [
    'display_name' => t('Process configurations'),
    'type' => 'batch'
  ];

   return $tasks;
}


function adm_batch_processing() {
  $components = \Drupal::state()->get('adm.enabled_components');
  $batch = [];

  if (!empty($components)) {
    foreach ($components as $component) {
      $batch[] = [
        'adm_batch_processing_enable_module',
        [$component],
      ];
    }
  }

  return ['operations' => $batch];
}

function adm_batch_processing_enable_module($module, &$context) {
  \Drupal::service('module_installer')->install([$module]);

}
