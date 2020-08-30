<?php

namespace Drupal\adm_core\EventSubscriber;

use Drupal\Core\Extension\ModuleHandlerInterface;
use Drupal\Core\Session\AccountInterface;
use Symfony\Component\EventDispatcher\Event;
use Symfony\Component\EventDispatcher\EventSubscriberInterface;
use Symfony\Component\HttpKernel\Exception\NotFoundHttpException;

/**
 * Event subscriber to disable taxonomy term paths.
 *
 * Show page not found by default for all taxonomy terms. It is possible
 * to disable this behaviour per vocabulary.
 *
 * @package Drupal\adm_core\AdmTaxonomySubscriber
 */
class AdmTaxonomySubscriber implements EventSubscriberInterface {

  /**
   * The current user.
   *
   * @var \Drupal\Core\Session\AccountInterface
   */
  protected $currentUser;

  /**
   * The module handler service.
   *
   * @var \Drupal\Core\Extension\ModuleHandlerInterface
   */
  protected $moduleHandler;

  /**
   * AdmTaxonomySubscriber constructor.
   *
   * @param \Drupal\Core\Session\AccountInterface $current_user
   *   The current user.
   * @param \Drupal\Core\Extension\ModuleHandlerInterface $module_handler
   *   The module handler service.
   */
  public function __construct(AccountInterface $current_user, ModuleHandlerInterface $module_handler) {
    $this->currentUser = $current_user;
    $this->moduleHandler = $module_handler;
  }

  /**
   * {@inheritdoc}
   */
  public static function getSubscribedEvents() {
    $events['kernel.request'] = ['onRequest', 27];

    return $events;
  }

  /**
   * Show not found page when requesting canonical route.
   *
   * @param \Symfony\Component\EventDispatcher\Event $event
   *   The event data object.
   */
  public function onRequest(Event $event): void {
    /** @var \Symfony\Component\HttpKernel\Event\GetResponseEvent $event */
    if ($event->getRequest()->get('exception') !== NULL) {
      return;
    }

    if (!$this->currentUser->hasPermission('administer taxonomy')
      && $event->getRequest()->get('_route') === 'entity.taxonomy_term.canonical') {

      /** @var \Drupal\taxonomy\Entity\Term $taxonomy_term */
      $taxonomy_term = $event->getRequest()->get('taxonomy_term');
      $skip_vocabularies = [];

      $this->moduleHandler->alter('adm_core_show_term_view', $skip_vocabularies);

      // If the current term is in list of allowed vocabularies,
      // then we allow showing term view.
      if (in_array($taxonomy_term->bundle(), $skip_vocabularies, TRUE)) {
        return;
      }

      throw new NotFoundHttpException();
    }
  }

}
