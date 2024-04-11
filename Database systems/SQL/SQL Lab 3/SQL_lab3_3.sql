/*
3) Improve the query in question 2 by displaying Cus_LName, Cus_FName instead of Cus_Code. Use proper, 
modern JOIN syntax to accomplish this. Add meaningful aliases to all columns.
*/

SELECT
    CONCAT(CUSTOMER.CUS_FNAME, ' ', CUSTOMER.CUS_LNAME) AS `Customer Name`,
    INVOICE.INV_NUMBER AS `Invoice Number`,
    PRODUCT.P_DESCRIPT AS `Product Description`,
    LINE.LINE_UNITS AS `Units Bought`,
    LINE.LINE_PRICE AS `Unit Price`,
    (LINE.LINE_UNITS * LINE.LINE_PRICE) AS `Subtotal`
FROM CUSTOMER
JOIN INVOICE ON CUSTOMER.CUS_CODE = INVOICE.CUS_CODE
JOIN LINE ON INVOICE.INV_NUMBER = LINE.INV_NUMBER
JOIN PRODUCT ON LINE.P_CODE = PRODUCT.P_CODE;
