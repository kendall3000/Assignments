EXPLAIN SELECT P_CODE, P_QOH * P_PRICE
FROM PRODUCT P
JOIN (
  SELECT AVG(P_QOH * P_PRICE) AS AVG_QOH_PRICE
  FROM PRODUCT
) AS AVG_TABLE ON P.P_QOH * P.P_PRICE > AVG_TABLE.AVG_QOH_PRICE;