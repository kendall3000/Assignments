// JavaScript Document

document.addEventListener('DOMContentLoaded', function() {
    var elUsername = document.getElementById('username');
    var elPassword = document.getElementById('password');
    var elEmail = document.getElementById('email');
    var elFirstname = document.getElementById('firstname');
    var elLastname = document.getElementById('lastname');
    var elPhone = document.getElementById('phone');
    var elComments = document.getElementById('comments');

    elUsername.addEventListener('blur', function () {
        checkUsername();
    });

    elPassword.addEventListener('blur', function () {
        checkPassword();
    });

    elEmail.addEventListener('blur', function () {
        checkEmail();
    });

    elFirstname.addEventListener('blur', function () {
        checkName(elFirstname);
    });

    elLastname.addEventListener('blur', function () {
        checkName(elLastname);
    });

    elPhone.addEventListener('blur', function () {
        checkPhone();
    });

    elComments.addEventListener('blur', function () {
        checkComments();
    });

    function checkUsername() {
        var username = elUsername.value;
        if (username.length < 6 || !username.trim()) {
            showError(elUsername, 'Username must be at least 6 characters long and cannot be empty');
        } else {
            showSuccess(elUsername);
        }
    }

    function checkPassword() {
        var password = elPassword.value;
        if (password.length < 6 || !password.trim()) {
            showError(elPassword, 'Password must be at least 6 characters long and cannot be empty');
        } else {
            showSuccess(elPassword);
        }
    }

    function checkEmail() {
        var email = elEmail.value;
        var validRegex = /^(([^<>()[\]\\.,;:\s@"]+(\.[^<>()[\]\\.,;:\s@"]+)*)|.(".+"))@((\[[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\])|(([a-zA-Z\-0-9]+\.)+[a-zA-Z]{2,}))$/;
        if (!email.match(validRegex)) {
            showError(elEmail, 'Invalid email address');
        } else {
            showSuccess(elEmail);
        }
    }

    function checkName(element) {
        var name = element.value;
        var validRegex = /^[A-Za-z'-]{2,}$/;
        if (!name.match(validRegex) || !name.trim()) {
            showError(element, 'Name must contain at least 2 alphabetical characters and cannot be empty');
        } else {
            showSuccess(element);
        }
    }

    function checkPhone() {
        var phone = elPhone.value;
        var validRegex = /^\d{10}$/;
        if (!phone.match(validRegex) || !phone.trim()) {
            showError(elPhone, 'Phone number must be exactly 10 digits and cannot be empty');
        } else {
            showSuccess(elPhone);
        }
    }

    function checkComments() {
        var comments = elComments.value;
        if (!comments.trim()) {
            showError(elComments, 'Comments cannot be empty');
        } else {
            showSuccess(elComments);
        }
    }

    function showError(input, message) {
        var feedback = input.nextElementSibling;
        feedback.innerHTML = message;
        feedback.classList.add('error');
        input.classList.add('error');
    }

    function showSuccess(input) {
        var feedback = input.nextElementSibling;
        feedback.innerHTML = '';
        feedback.classList.remove('error');
        input.classList.remove('error');
    }
});
