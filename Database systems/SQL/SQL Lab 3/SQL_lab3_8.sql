/*
8) Advertising has requested a list of all customers who have never made a purchase, along with the 
customer's name and phone number. Provide them with a query with this information. Display the name in the 
style you believe would be most useful - briefly explain your choice in the comments.
*/

SELECT 
    CONCAT(CUSTOMER.CUS_FNAME, ' ', CUSTOMER.CUS_LNAME) AS `Customer Name`,
    CUSTOMER.CUS_PHONE AS `Customer Phone`
FROM CUSTOMER
WHERE CUSTOMER.CUS_CODE NOT IN (SELECT DISTINCT CUS_CODE FROM INVOICE);
