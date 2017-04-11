<?php
  /*
   * @file
   * Template for Webform POST Redirect Page.
   *
   * Available variables:
   * $form: The hidden form that sends webform data
   * $page_title: The page title
   * $message: The page text
   */
?>
<div id='webform_post_redirect_page'>
  <h1><?php print render($page_title); ?></h1>

  <img src="<?php echo base_path() . drupal_get_path('module', 'webform_post_redirect'); ?>/images/loading.gif" class="centered" />
  <br/>

  <div id='webform_post_redirect_message'>
    <?php print render($message); ?>
  </div>

  <?php print render($form); ?>
</div>
