/*
2) Generate a list of customer purchases, including subtotals for the invoice line numbers. Subtotals are a 
derived attribute, calculated by multipying Line_Units by Line_Price). Columns displayed should be Cus_Code, 
Inv_Number, P_Description, Units Bought (this is an alias), Unit Price (alias) and Subtotal (alias). It is up 
to you to determine which columns you will use to create the aliases.
*/

SELECT
    CUSTOMER.CUS_CODE, INVOICE.INV_NUMBER, PRODUCT.P_DESCRIPT,
    LINE.LINE_UNITS AS `Units Bought`,
    LINE.LINE_PRICE AS `Unit Price`,
    (LINE.LINE_UNITS * LINE.LINE_PRICE) AS `Subtotal`
FROM CUSTOMER
JOIN INVOICE ON CUSTOMER.CUS_CODE = INVOICE.CUS_CODE
JOIN LINE ON INVOICE.INV_NUMBER = LINE.INV_NUMBER
JOIN PRODUCT ON LINE.P_CODE = PRODUCT.P_CODE;
