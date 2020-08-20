<?php

/**
 * @file
 * Create default nodes.
 */

use Drupal\node\Entity\Node;

/**
 * Create default nodes.
 */
function adm_default_content_create_default_nodes($paragraphs) {
  $front_page = Node::create([
    'type' => 'page',
    'uid' => 1,
    'title' => 'Front Page',
    'status' => 1,
  ]);

  $front_page->get('field_page_components')->appendItem([
    'target_id' => $paragraphs['carousel']->id(),
    'target_revision_id' => $paragraphs['carousel']->getRevisionId(),
  ]);

  $front_page->save();

  $page_403 = Node::create([
    'type' => 'page',
    'uid' => 1,
    'title' => 'Access denied',
    'status' => 1,
  ]);
  $page_403->save();

  $page_404 = Node::create([
    'type' => 'page',
    'uid' => 1,
    'title' => 'Page not found',
    'status' => 1,
  ]);
  $page_404->save();

}
