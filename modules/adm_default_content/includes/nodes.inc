<?php

/**
 * @file
 * Create default nodes.
 */

use Drupal\node\Entity\Node;
use Drupal\node\NodeInterface;

/**
 * Create default nodes.
 */
function adm_default_content_create_default_nodes($paragraphs) {
  $front_page = Node::create([
    'type' => 'page',
    'uid' => 1,
    'title' => 'Front Page',
    'status' => NodeInterface::PUBLISHED,
  ]);

  $front_page->get('field_page_components')->appendItem([
    'target_id' => $paragraphs['carousel']->id(),
    'target_revision_id' => $paragraphs['carousel']->getRevisionId(),
  ]);

  $front_page->set('moderation_state', 'published');

  $front_page->save();

  $page_403 = Node::create([
    'type' => 'page',
    'uid' => 1,
    'title' => 'Access denied',
    'status' => NodeInterface::PUBLISHED,
  ]);
  $page_403->set('moderation_state', 'published');
  $page_403->save();

  $page_404 = Node::create([
    'type' => 'page',
    'uid' => 1,
    'title' => 'Page not found',
    'status' => NodeInterface::PUBLISHED,
  ]);
  $page_404->set('moderation_state', 'published');
  $page_404->save();
}
