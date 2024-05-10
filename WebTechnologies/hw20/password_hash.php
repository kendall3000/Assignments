<?php
function hashPassword($password) {
    // Generate a random salt
    $salt = random_bytes(16);
    
    // Hash the password with SHA-256
    $hashedPassword = hash('sha256', $password . $salt);
    
    // Concatenate the salt and hashed password for storage
    $storedPassword = $salt . $hashedPassword;
    
    return $storedPassword;
}
?>
