SELECT CONCAT(PATRON.PAT_FNAME, ' ',PATRON.PAT_LNAME) AS PATRON_NAME, BOOK.BOOK_TITLE, 
	   DATEDIFF(CHECKOUT.CHECK_IN_DATE, CHECKOUT.CHECK_OUT_DATE) AS DAYS_KEPT
FROM PATRON
JOIN CHECKOUT ON PATRON.PAT_ID = CHECKOUT.PAT_ID
JOIN BOOK ON CHECKOUT.BOOK_NUM = BOOK.BOOK_NUM;

