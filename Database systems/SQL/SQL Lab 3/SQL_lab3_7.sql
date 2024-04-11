/*
7) Write a query that provides the total number of invoices, the sales total for all invoices, the 
smallest purchase amount, largest purchase amount, and average purchase amount. You should use aliases 
to make your output look reasonable for a business user.
*/

SELECT
    COUNT(INVOICE.INV_NUMBER) AS `Total Invoices`,
    SUM(LINE.LINE_UNITS * LINE.LINE_PRICE) AS `Total Sales`,
    MIN(LINE.LINE_UNITS * LINE.LINE_PRICE) AS `Smallest Purchase Amount`,
    MAX(LINE.LINE_UNITS * LINE.LINE_PRICE) AS `Largest Purchase Amount`,
    AVG(LINE.LINE_UNITS * LINE.LINE_PRICE) AS `Average Purchase Amount`
FROM INVOICE
LEFT JOIN LINE ON INVOICE.INV_NUMBER = LINE.INV_NUMBER;
