/* 1) List all purchases made by customers. Your query should return the Cus_Code, Inv_Number, 
Inv_Date, P_Descript, Line_Units and Line_Price. Sort by Customer code, invoice number, and 
product description in that order.
*/

SELECT
    CUSTOMER.CUS_CODE, INVOICE.INV_NUMBER, INVOICE.INV_DATE,
    PRODUCT.P_DESCRIPT, LINE.LINE_UNITS, LINE.LINE_PRICE
FROM CUSTOMER
JOIN INVOICE ON CUSTOMER.CUS_CODE = INVOICE.CUS_CODE
JOIN LINE ON INVOICE.INV_NUMBER = LINE.INV_NUMBER
JOIN PRODUCT ON LINE.P_CODE = PRODUCT.P_CODE
ORDER BY CUSTOMER.CUS_CODE, INVOICE.INV_NUMBER, PRODUCT.P_DESCRIPT;
