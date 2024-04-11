/*
Query 6: Calculate the average purchase amount for each customer to query 5. Your column headers should be Customer Last Name, 
Customer First Name, Total Purchases, Number of Purchases, and Average Purchase Amount. The average purchase amount is 
calculated for each customer.
*/

SELECT
    CUSTOMER.CUS_LNAME AS `Customer Last Name`,
    CUSTOMER.CUS_FNAME AS `Customer First Name`,
    CUSTOMER.CUS_BALANCE AS `Customer Balance`,
    SUM(LINE.LINE_UNITS * LINE.LINE_PRICE) AS `Total Purchases`,
    COUNT(INVOICE.INV_NUMBER) AS `Number of Purchases`,
    SUM(LINE.LINE_UNITS * LINE.LINE_PRICE) / COUNT(INVOICE.INV_NUMBER) AS `Average Purchase Amount`
FROM CUSTOMER
LEFT JOIN INVOICE ON CUSTOMER.CUS_CODE = INVOICE.CUS_CODE
LEFT JOIN LINE ON INVOICE.INV_NUMBER = LINE.INV_NUMBER
GROUP BY `Customer Last Name`, `Customer First Name`, `Customer Balance`;



