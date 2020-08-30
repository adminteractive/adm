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

/**
 * Add taxonomy term bundles to show publicly.
 *
 * By default, adm distribution hides all taxonomy term view paths from public,
 * most of the times these paths are forgotten and may expose data
 * which shouldn't be visible for other users.
 * This alter hook allows to expose specific taxonomy term bundles.
 *
 * @param array $skip_vocabularies
 *   The list of taxonomy term bundles to show publicly.
 */
function hook_adm_core_show_term_view_alter(array &$skip_vocabularies) {
  $skip_vocabularies[] = 'tags';
}
