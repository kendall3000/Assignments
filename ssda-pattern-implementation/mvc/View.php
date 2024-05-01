<?php
class View {
    public function renderValidationError($errorCode) {
        echo "Validation error occurred with error code: $errorCode";
    }

    public function renderRegistrationSuccess($username) {
        echo "Registration successful! Welcome, $username";
    }
}
?>
