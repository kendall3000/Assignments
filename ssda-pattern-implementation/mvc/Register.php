<?php
require_once 'RegistrationController.php';

$registrationController = new RegistrationController();
$registrationController->registerUser($_POST['username'], $_POST['password1'], $_POST['password2']);
?>
