/*9) Find out who has books currently checked out. You should return the patron's first name, last name, and book title.*/

SELECT PATRON.PAT_FNAME,PATRON.PAT_LNAME, BOOK.BOOK_TITLE
FROM PATRON
JOIN CHECKOUT ON PATRON.PAT_ID = CHECKOUT.PAT_ID
JOIN BOOK ON CHECKOUT.BOOK_NUM = BOOK.BOOK_NUM
WHERE CHECKOUT.CHECK_IN_DATE IS NULL;
