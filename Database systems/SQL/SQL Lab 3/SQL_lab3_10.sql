/*
10) Which Vendor does this company use the most frequently to supply products? Display the Vendor's
 name with the most products currently in the Product Table as well as the total number of 
 products for that particular vendor. This query should display correctly if there is a tie between 
 two vendors and if the data in the product table changes (e.g. we begin ordering more products from 
 a particular vendor).
*/

SELECT
    V.V_NAME AS `Vendor Name`,
    COUNT(P.P_CODE) AS `Total Products`
FROM VENDOR V
LEFT JOIN PRODUCT P ON V.V_CODE = P.V_CODE
GROUP BY `Vendor Name`
ORDER BY `Total Products` DESC
LIMIT 3;
