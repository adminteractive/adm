(function ($) {

  /**
   * Image resize functionality.
   * Allow resetting values and keep aspect ratio.
   *
   * @type {{attach: Drupal.behaviors.AdmMediaImageResize.attach}}
   */
  Drupal.behaviors.AdmMediaImageResize = {
    attach: function () {
      const $container = $('.adm-media--dimensions');
      const $reset = $('.adm-media--reset', $container);
      const $width = $('.adm-media--image-width', $container);
      const $height = $('.adm-media--image-height', $container);
      const orig_width = $reset.data('width');
      const orig_height = $reset.data('height');

      $reset.on('click', function (e) {
        e.preventDefault();

        $width.val(orig_width);
        $height.val(orig_height);

      });

      $width.on('change', function () {
        let value = $(this).val();

        if ( value && value !== '0' ) {
          value = Math.round( orig_height * ( value / orig_width ) );
        }

        if ( !isNaN( value ) ) {
          $height.val(value);
        }
      });

      $height.on('change', function () {
        let value = $(this).val();

        if ( value && value !== '0' ) {
          value = Math.round( orig_width * ( value / orig_height ) );
        }

        if ( !isNaN( value ) ) {
          $width.val(value);
        }
      });

    }
  }
})(jQuery);
