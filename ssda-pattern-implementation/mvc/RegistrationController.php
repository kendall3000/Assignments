<?php
require_once 'Database.php';
require_once 'View.php';

class RegistrationController {
    private $db;
    private $view;

    public function __construct() {
        $this->db = new Database();
        $this->view = new View();
    }

    public function registerUser($username, $password1, $password2) {
        // Validation logic
        if ($password1 != $password2 || !$this->isValid($password1) || !$this->isValid($username)) {
            $this->view->renderValidationError(400);
            return;
        }

        // Hash the password
        $pwHash = hash('sha256', $password1);

        // Insert user into database
        $success = $this->db->query("INSERT INTO users (username, password) VALUES ('$username', '$pwHash')");

        if (!$success) {
            $this->view->renderValidationError(500);
            return;
        }

        $this->view->renderRegistrationSuccess($username);
    }

    private function isValid($data) {
        // Placeholder for validation logic
        return true;
    }
}
?>
