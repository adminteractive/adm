<?php

/**
 * @file
 * Create default nodes.
 */

use Drupal\node\Entity\Node;

/**
 * Create default nodes.
 */
function adm_default_content_create_default_nodes() {
  $front_page = Node::create([
    'type' => 'page',
    'langcode' => 'et',
    'uid' => 1,
    'title' => 'Avaleht',
  ]);

  $front_page->save();

  $page_403 = Node::create([
    'type' => 'page',
    'langcode' => 'et',
    'uid' => 1,
    'title' => 'Ligipääs keelatud',
  ]);
  $page_403->save();

  $page_404 = Node::create([
    'type' => 'page',
    'langcode' => 'et',
    'uid' => 1,
    'title' => 'Lehte ei leitud',
  ]);
  $page_404->save();

}
