<?php
namespace Drupal\adm_core\Form;

use Drupal\Core\Form\ConfigFormBase;
use Drupal\Core\Form\FormStateInterface;

class FooterSettings extends ConfigFormBase {

  /**
   * Gets the configuration names that will be editable.
   *
   * @return array
   *   An array of configuration object names that are editable if called in
   *   conjunction with the trait's config() method.
   */
  protected function getEditableConfigNames() {
    return ['adm_core.footer_settings'];
  }

  /**
   * Returns a unique string identifying the form.
   *
   * The returned ID should be a unique string that can be a valid PHP function
   * name, since it's used in hook implementation names such as
   * hook_form_FORM_ID_alter().
   *
   * @return string
   *   The unique string identifying the form.
   */
  public function getFormId() {
    return 'adm_core.footer_settings';
  }

  public function buildForm(array $form, FormStateInterface $form_state) {
    $form = parent::buildForm($form, $form_state);
    $config = $this->config('adm_core.footer_settings');
    $items = $config->get('footer_content');
    $social_icons = _adm_core_social_media_types();

    $form['social_icons'] = [
      '#type' => 'fieldset',
      '#title' => $this->t('Social icons'),
      '#description' => $this->t('Specify social media links. If the url field is empty, then the icon will be hidden.'),
      '#tree' => TRUE,
    ];

    foreach ($social_icons as $icon => $label) {
      $form['social_icons'][$icon] = [
        '#type' => 'url',
        '#title' => $label,
        '#default_value' => $config->get('social_icons.' . $icon . '.url'),
      ];
    }

    $form['item'] = [
      '#type' => 'container',
      '#tree' => TRUE,
    ];

    for ($i = 0; $i <= 2; $i++) {
      $form['item'][$i] = [
        '#type' => 'fieldset',
        '#title' => $this->t('Column @id', ['@id' => $i + 1]),
      ];

      $form['item'][$i]['column_title'] = [
        '#type' => 'textfield',
        '#title' => $this->t('Column title'),
        '#default_value' => $items[$i]['column_title'],
      ];

      $form['item'][$i]['column_content'] = [
        '#type' => 'text_format',
        '#title' => $this->t('Column content'),
        '#default_value' => $items[$i]['column_content']['value'],
        '#format' => $items[$i]['column_content']['format'],
      ];
    }

    return $form;
  }

  public function submitForm(array &$form, FormStateInterface $form_state) {
    parent::submitForm($form, $form_state);

    $footer_content = [];

    foreach ($form_state->getValue('item', []) as $key => $item) {
      $footer_content[$key] = $item;
    }

    $icons = [];

    foreach ($form_state->getValue('social_icons') as $type => $url) {
      $icons[$type] = [
        'type' => $type,
        'url' => $url,
      ];
    }

    $this->config('adm_core.footer_settings')
      ->set('footer_content', $footer_content)
      ->set('social_icons', $icons)
      ->save();
  }


}
