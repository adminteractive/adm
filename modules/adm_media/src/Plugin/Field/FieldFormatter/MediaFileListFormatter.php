<?php

namespace Drupal\adm_media\Plugin\Field\FieldFormatter;

use Drupal\Component\Plugin\Exception\PluginException;
use Drupal\Core\Entity\EntityTypeManagerInterface;
use Drupal\Core\Field\FieldDefinitionInterface;
use Drupal\Core\Field\FieldItemListInterface;
use Drupal\Core\Field\Plugin\Field\FieldFormatter\EntityReferenceFormatterBase;
use Drupal\Core\Template\Attribute;
use Drupal\Core\Url;
use Symfony\Component\DependencyInjection\ContainerInterface;

/**
 * Plugin implementation of the 'adm_media_file_list' formatter.
 *
 * @FieldFormatter(
 *   id = "adm_media_file_list",
 *   label = @Translation("ADM File list"),
 *   field_types = {
 *     "entity_reference",
 *   }
 * )
 */
class MediaFileListFormatter extends EntityReferenceFormatterBase {

  /**
   * The entity type manager service.
   *
   * @var \Drupal\Core\Entity\EntityTypeManagerInterface
   */
  protected $entityTypeManager;

  /**
   * Constructs a MediaFileListFormatter object.
   *
   * @param string $plugin_id
   *   The plugin_id for the formatter.
   * @param mixed $plugin_definition
   *   The plugin implementation definition.
   * @param \Drupal\Core\Field\FieldDefinitionInterface $field_definition
   *   The definition of the field to which the formatter is associated.
   * @param array $settings
   *   The formatter settings.
   * @param string $label
   *   The formatter label display setting.
   * @param string $view_mode
   *   The view mode.
   * @param array $third_party_settings
   *   Any third party settings.
   * @param \Drupal\Core\Entity\EntityTypeManagerInterface $entity_type_manager
   *   The entity type manager service.
   */
  public function __construct($plugin_id, $plugin_definition, FieldDefinitionInterface $field_definition, array $settings, $label, $view_mode, array $third_party_settings, EntityTypeManagerInterface $entity_type_manager) {
    parent::__construct($plugin_id, $plugin_definition, $field_definition, $settings, $label, $view_mode, $third_party_settings);

    $this->entityTypeManager = $entity_type_manager;
  }

  /**
   * {@inheritdoc}
   */
  public static function create(ContainerInterface $container, array $configuration, $plugin_id, $plugin_definition) {
    return new static(
      $plugin_id,
      $plugin_definition,
      $configuration['field_definition'],
      $configuration['settings'],
      $configuration['label'],
      $configuration['view_mode'],
      $configuration['third_party_settings'],
      $container->get('entity_type.manager')
    );
  }

  /**
   * {@inheritdoc}
   */
  public static function isApplicable(FieldDefinitionInterface $field_definition) {
    $settings = $field_definition->getSettings();

    return $settings['handler'] === 'default:media';
  }

  /**
   * Builds a renderable array for a field value.
   *
   * @param \Drupal\Core\Field\FieldItemListInterface $items
   *   The field values to be rendered.
   * @param string $langcode
   *   The language that should be used to render the field.
   *
   * @return array
   *   A renderable array for $items, as an array of child elements keyed by
   *   consecutive numeric indexes starting from 0.
   */
  public function viewElements(FieldItemListInterface $items, $langcode): array {
    $elements = [];
    $list_items = [];
    /** @var \Drupal\field\Entity\FieldConfig $definition */
    $definition = $items->getFieldDefinition();

    foreach ($this->getEntitiesToView($items, $langcode) as $delta => $entity) {
      /** @var \Drupal\media\Entity\Media $entity */
      try {
        /** @var \Drupal\media\Entity\MediaType $type */
        $type = $this->entityTypeManager->getStorage('media_type')
          ->load($entity->bundle());
      }
      catch (PluginException $e) {
        continue;
      }

      $source_field = $type->getSource()->getConfiguration()['source_field'];
      if ($entity->hasField($source_field) && !$entity->get($source_field)->isEmpty()) {
        /** @var \Drupal\file\Entity\File $file */
        $file = $entity->get($source_field)->entity;
        $list_items[$delta] = [
          'link' => [
            '#type' => 'link',
            '#url' => Url::fromRoute('media_entity_download.download', ['media' => $entity->id()]),
            '#title' => $entity->label(),
            '#cache' => [
              'tags' => $entity->getCacheTags(),
              'contexts' => $entity->getCacheContexts(),
            ],
          ],
          'file' => $file,
          'attributes' => new Attribute(),
        ];
      }
    }

    if (!empty($list_items)) {
      $elements = [
        '#theme' => 'adm_media_files_list',
        '#files' => $list_items,
        '#items' => $items,
        '#title' => $this->t('Related documents'),
        '#cache' => [
          'tags' => $definition->getCacheTags(),
          'contexts' => $definition->getCacheContexts(),
        ],
      ];
    }

    return $elements;
  }

}
