<?php
namespace Drupal\adm\Form;

use Drupal\Console\Bootstrap\Drupal;
use Drupal\Core\Form\FormBase;
use Drupal\Core\Form\FormStateInterface;
use Drupal\user\Entity\User;

class AdmConfigurationsForm extends FormBase {

  /**
   * Returns a unique string identifying the form.
   *
   * @return string
   *   The unique string identifying the form.
   */
  public function getFormId() {
    return 'adm_configurations_form';
  }

  /**
   * Form constructor.
   *
   * @param array $form
   *   An associative array containing the structure of the form.
   * @param \Drupal\Core\Form\FormStateInterface $form_state
   *   The current state of the form.
   *
   * @return array
   *   The form structure.
   */
  public function buildForm(array $form, FormStateInterface $form_state) {
    $form['editor'] = [
      '#type' => 'fieldset',
      '#title' => $this->t('Editor account'),
      '#description' => $this->t('Create editor account if needed.'),
      '#tree' => TRUE,
    ];

    $form['editor']['username'] = [
      '#type' => 'textfield',
      '#title' => $this->t('Username')
    ];

    $form['editor']['email'] = [
      '#type' => 'email',
      '#title' => $this->t('E-mail')
    ];

    $form['editor']['password'] = [
      '#type' => 'password_confirm',
    ];

    $form['actions'] = [
      '#type' => 'actions',
    ];

    $form['actions']['submit'] = [
      '#type' => 'submit',
      '#value' => $this->t('Next'),
    ];

    return $form;
  }

  public function validateForm(array &$form, FormStateInterface $form_state) {
    if (!$form_state->isValueEmpty(['editor', 'username']) || !$form_state->isValueEmpty(['editor', 'email'])) {
      $editor = $form_state->getValue('editor');

      if (empty($editor['username'])) {
        $form_state->setErrorByName('editor][username', $this->t('Username must be set!'));
      }

      if (empty($editor['email'])) {
        $form_state->setErrorByName('editor][email', $this->t('Email must be set!'));
      }

      if (empty($editor['password'])) {
        $form_state->setErrorByName('editor][password', $this->t('Password must be set!'));
      }
    }
  }

  /**
   * Form submission handler.
   *
   * @param array $form
   *   An associative array containing the structure of the form.
   * @param \Drupal\Core\Form\FormStateInterface $form_state
   *   The current state of the form.
   */
  public function submitForm(array &$form, FormStateInterface $form_state) {
    $editor = $form_state->getValue('editor');

    if (!empty($editor)) {
      $user = User::create([
        'name' => $editor['username'],
        'mail' => $editor['email'],
        'roles' => ['editor'],
        'password' => $editor['password'],
      ]);
      $user->save();
    }
  }
}
