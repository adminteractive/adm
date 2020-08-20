<?php

use Drupal\Core\File\FileSystemInterface;
use Drupal\media\Entity\Media;

/**
 * Create default media entities.
 */
function adm_default_content_create_default_media() {
  $media = [];
  /** @var \Drupal\Core\File\FileSystemInterface $file_system */
  $file_system = \Drupal::service('file_system');
  $directory = 'public://adm-samples';
  $file_system->prepareDirectory($directory, FileSystemInterface::CREATE_DIRECTORY);
  $module_path = drupal_get_path('module', 'adm_default_content') . '/sample-images';


  $image = file_get_contents($module_path . '/bird.jpg');
  $file = file_save_data($image, $directory . '/bird.jpg', FileSystemInterface::EXISTS_REPLACE);

  $item = Media::create([
    'bundle' => 'image',
    'uid' => 1,
    'name' => $file->getFilename(),
    'field_media_image' => [
      'target_id' => $file->id(),
    ],
  ]);
  $item->save();
  $media[] = $item;

  $image = file_get_contents($module_path . '/butterfly.jpg');
  $file = file_save_data($image, $directory . '/butterfly.jpg', FileSystemInterface::EXISTS_REPLACE);

  $item = Media::create([
    'bundle' => 'image',
    'uid' => 1,
    'name' => $file->getFilename(),
    'field_media_image' => [
      'target_id' => $file->id(),
    ],
  ]);
  $item->save();
  $media[] = $item;

  $image = file_get_contents($module_path . '/cone.jpg');
  $file = file_save_data($image, $directory . '/cone.jpg', FileSystemInterface::EXISTS_REPLACE);

  $item = Media::create([
    'bundle' => 'image',
    'uid' => 1,
    'name' => $file->getFilename(),
    'field_media_image' => [
      'target_id' => $file->id(),
    ],
  ]);
  $item->save();
  $media[] = $item;

  return $media;
}
