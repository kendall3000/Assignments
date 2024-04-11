/*
4) Write a query to display the Customer's Name (same format as above), the Cus_Balance and Total purchases for 
each customer. Total purchases is calculated by summing subtotals from problem 3.
*/
SELECT
    CONCAT(CUSTOMER.CUS_FNAME, ' ', CUSTOMER.CUS_LNAME) AS `Customer Name`,
    CUSTOMER.CUS_BALANCE AS `Customer Balance`,
    SUM(LINE.LINE_UNITS * LINE.LINE_PRICE) AS `Total Purchases`
FROM CUSTOMER
LEFT JOIN INVOICE ON CUSTOMER.CUS_CODE = INVOICE.CUS_CODE
LEFT JOIN LINE ON INVOICE.INV_NUMBER = LINE.INV_NUMBER
GROUP BY `Customer Name`, `Customer Balance`;
