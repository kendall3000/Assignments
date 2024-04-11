EXPLAIN SELECT P_CODE, P_PRICE
FROM PRODUCT P
JOIN (SELECT AVG(P_PRICE) AS AVG_PRICE FROM PRODUCT) AS AVG_TABLE
WHERE P.P_PRICE >= AVG_TABLE.AVG_PRICE;
