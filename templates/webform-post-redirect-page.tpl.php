<?php
  /*
   * @file
   * Template for Webform POST Redirect Page.
   *
   * Available variables:
   * $form: The hidden form that sends webform data
   * $header: The page header
   * $message: The page text
   */
?>
<div id='webform_post_redirect_page'>
  <h1><?php print render($header); ?></h1>

  <img src="<?php echo base_path() . drupal_get_path('module', 'webform_post_redirect'); ?>/images/loading.gif" class="centered" />
  <br/>

  <p><?php print render($message); ?></p>

  <?php print render($form); ?>
</div>
