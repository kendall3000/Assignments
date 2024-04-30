<html>
<body>
    <p>Welcome to my Home Page!</p>
    <?php
        $today = date("F j, Y");
        $tomorrow = date("F j, Y", strtotime("+1 day")); 
        echo "<p>Today is: $today</p>";
        echo "<p>Tomorrow is: $tomorrow</p>";
    ?>
</body>
</html>
