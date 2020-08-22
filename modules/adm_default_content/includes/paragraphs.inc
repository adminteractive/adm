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


  $grid_1 = Paragraph::create([
    'type' => 'text_section',
    'status' => 1,
    'field_text_section_content' => [
      'value' => '<p class="lead">Praesent vestibulum dapibus nibh. Praesent venenatis metus at tortor pulvinar varius. Phasellus gravida semper nisi. Etiam feugiat lorem non metus. Suspendisse pulvinar, augue ac venenatis condimentum, sem libero volutpat nibh, nec pellentesque velit pede quis nunc.</p>
<p>Mauris turpis nunc, blandit et, volutpat molestie, porta ut, ligula. Etiam ultricies nisi vel augue. Ut non enim eleifend felis pretium feugiat. Fusce egestas elit eget lorem. Nunc nulla.</p>
<p>Praesent ut ligula non mi varius sagittis. Ut id nisl quis enim dignissim sagittis. Sed a libero. Nunc nonummy metus. Fusce a quam.</p>',
      'format' => 'full_html'
    ]
  ]);
  $grid_1->save();

  $grid_2 = Paragraph::create([
    'type' => 'text_section',
    'status' => 1,
    'field_text_section_content' => [
      'value' => '<p>Praesent vestibulum dapibus nibh. Praesent venenatis metus at tortor pulvinar varius. Phasellus gravida semper nisi. Etiam feugiat lorem non metus. Suspendisse pulvinar, augue ac venenatis condimentum, sem libero volutpat nibh, nec pellentesque velit pede quis nunc.</p>
<p>Mauris turpis nunc, blandit et, volutpat molestie, porta ut, ligula. Etiam ultricies nisi vel augue. Ut non enim eleifend felis pretium feugiat. Fusce egestas elit eget lorem. Nunc nulla.</p>
<p>Praesent ut ligula non mi varius sagittis. Ut id nisl quis enim dignissim sagittis. Sed a libero. Nunc nonummy metus. Fusce a quam.</p>',
      'format' => 'full_html',
    ]
  ]);
  $grid_2->save();

  $grid_3 = Paragraph::create([
    'type' => 'text_section',
    'status' => 1,
    'field_text_section_content' => [
      'value' => '<p>Praesent vestibulum dapibus nibh. Praesent venenatis metus at tortor pulvinar varius. Phasellus gravida semper nisi. Etiam feugiat lorem non metus. Suspendisse pulvinar, augue ac venenatis condimentum, sem libero volutpat nibh, nec pellentesque velit pede quis nunc.</p>
<p>Mauris turpis nunc, blandit et, volutpat molestie, porta ut, ligula. Etiam ultricies nisi vel augue. Ut non enim eleifend felis pretium feugiat. Fusce egestas elit eget lorem. Nunc nulla.</p>
<p>Praesent ut ligula non mi varius sagittis. Ut id nisl quis enim dignissim sagittis. Sed a libero. Nunc nonummy metus. Fusce a quam.</p>',
      'format' => 'full_html'
    ]
  ]);
  $grid_3->save();

  $paragraphs['grid'] = Paragraph::create([
    'type' => 'grid',
    'status' => 1,
    'field_grid_title' => [
      'value' => 'ADM Distribution successfully installed!'
    ],
  ]);

  $paragraphs['grid']->get('field_grid_items')->appendItem([
    'target_id' => $grid_1->id(),
    'target_revision_id' => $grid_1->getRevisionId(),
  ]);

  $paragraphs['grid']->get('field_grid_items')->appendItem([
    'target_id' => $grid_2->id(),
    'target_revision_id' => $grid_2->getRevisionId(),
  ]);

  $paragraphs['grid']->get('field_grid_items')->appendItem([
    'target_id' => $grid_3->id(),
    'target_revision_id' => $grid_3->getRevisionId(),
  ]);

  $paragraphs['grid']->save();

  return $paragraphs;
}
