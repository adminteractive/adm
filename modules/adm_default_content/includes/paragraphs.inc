<?php

use Drupal\paragraphs\Entity\Paragraph;

/**
 * @param \Drupal\media\MediaInterface[] $media
 *
 * @return array
 * @throws \Drupal\Component\Plugin\Exception\InvalidPluginDefinitionException
 * @throws \Drupal\Component\Plugin\Exception\PluginNotFoundException
 * @throws \Drupal\Core\Entity\EntityStorageException
 */
function adm_default_content_create_default_front_paragraphs($media) {
  $paragraphs = [];

  $slide_1 = Paragraph::create([
    'type' => 'carousel_item',
    'status' => 1,
    'field_carousel_item_image' => [
      'target_id' => $media[0]->id(),
    ]
  ]);
  $slide_1->save();

  $slide_2 = Paragraph::create([
    'type' => 'carousel_item',
    'status' => 1,
    'field_carousel_item_image' => [
      'target_id' => $media[1]->id(),
    ]
  ]);
  $slide_2->save();

  $slide_3 = Paragraph::create([
    'type' => 'carousel_item',
    'status' => 1,
    'field_carousel_item_image' => [
      'target_id' => $media[2]->id(),
    ]
  ]);
  $slide_3->save();

  $paragraphs['carousel'] = Paragraph::create([
    'type' => 'carousel',
    'status' => 1,
  ]);

  $paragraphs['carousel']->get('field_carousel_item')->appendItem([
    'target_id' => $slide_1->id(),
    'target_revision_id' => $slide_1->getRevisionId(),
  ]);

  $paragraphs['carousel']->get('field_carousel_item')->appendItem([
    'target_id' => $slide_2->id(),
    'target_revision_id' => $slide_2->getRevisionId(),
  ]);

  $paragraphs['carousel']->get('field_carousel_item')->appendItem([
    'target_id' => $slide_3->id(),
    'target_revision_id' => $slide_3->getRevisionId(),
  ]);

  $paragraphs['carousel']->save();


  return $paragraphs;
}
