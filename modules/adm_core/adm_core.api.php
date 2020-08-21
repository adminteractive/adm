<?php

/**
 * @file
 * Documentation of alter hooks defined by adm_core module.
 */

/**
 * Alter the list of social media types.
 *
 * @param array $social_media
 *   Associative array of social media types.
 */
function hook_adm_core_social_media_types_alter(array &$social_media) {
  $social_media['instagram'] = 'Instagram';
}
