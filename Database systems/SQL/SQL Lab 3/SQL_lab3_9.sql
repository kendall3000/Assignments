/*
9) Calculate the value of products currently in inventory. The value of the products can be calculated 
using P_QOH (quantity on hand) and P_Price. Display results with a subtotal for each different product.
You should display the P_Descript, P_QOH, P_Price, and Subtotal for each product. Use aliases to improve 
the display.
*/

SELECT
    P_DESCRIPT AS `Product Description`,
    P_QOH AS `Quantity On Hand`,
    P_PRICE AS `Unit Price`,
    (P_QOH * P_PRICE) AS `Subtotal`
FROM PRODUCT;
