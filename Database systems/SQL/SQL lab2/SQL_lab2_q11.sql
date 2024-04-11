/*11) Write a question and a query of your own that joins a minimum of three tables. Think about what information might 
be useful from this database. Describe the information you want your query to return, write the query and display the results.
*/

-- Kendall's Question
/* IS there any patron that checks out books from the same author if true list the patron first name, last name, the authors full
name and the book titles. If false return "there are no consistent patrons." Group the patrons name together with the author 
in ascending order and list how many times they have gotten a book from the author. */

SELECT DISTINCT PATRON.PAT_FNAME, PATRON.PAT_LNAME, CONCAT(AUTHOR.AU_FNAME, ' ', AUTHOR.AU_LNAME) AS AUTHOR_NAME, BOOK.BOOK_TITLE
FROM PATRON
JOIN CHECKOUT ON PATRON.PAT_ID = CHECKOUT.PAT_ID
JOIN BOOK ON CHECKOUT.BOOK_NUM = BOOK.BOOK_NUM
JOIN WRITES ON BOOK.BOOK_NUM = WRITES.BOOK_NUM
JOIN AUTHOR ON WRITES.AU_ID = AUTHOR.AU_ID
WHERE (PATRON.PAT_ID, AUTHOR.AU_ID) IN (
    SELECT CHECKOUT.PAT_ID, WRITES.AU_ID
    FROM CHECKOUT
    JOIN BOOK ON CHECKOUT.BOOK_NUM = BOOK.BOOK_NUM
    JOIN WRITES ON BOOK.BOOK_NUM = WRITES.BOOK_NUM
)
ORDER BY PATRON.PAT_FNAME, PATRON.PAT_LNAME, AUTHOR_NAME, BOOK.BOOK_TITLE;

/*SELECT
    PATRON.PAT_FNAME,
    PATRON.PAT_LNAME,
    CONCAT(AUTHOR.AU_FNAME, ' ', AUTHOR.AU_LNAME) AS AUTHOR_NAME,
    BOOK.BOOK_TITLE,
    COUNT(*) AS NUM_CHECKOUTS
FROM PATRON
JOIN CHECKOUT ON PATRON.PAT_ID = CHECKOUT.PAT_ID
JOIN BOOK ON CHECKOUT.BOOK_NUM = BOOK.BOOK_NUM
JOIN WRITES ON BOOK.BOOK_NUM = WRITES.BOOK_NUM
JOIN AUTHOR ON WRITES.AU_ID = AUTHOR.AU_ID
WHERE (PATRON.PAT_ID, AUTHOR.AU_ID) IN (
    SELECT CHECKOUT.PAT_ID, WRITES.AU_ID
    FROM CHECKOUT
    JOIN BOOK ON CHECKOUT.BOOK_NUM = BOOK.BOOK_NUM
    JOIN WRITES ON BOOK.BOOK_NUM = WRITES.BOOK_NUM
)
GROUP BY PATRON.PAT_FNAME, PATRON.PAT_LNAME, AUTHOR_NAME, BOOK.BOOK_TITLE
ORDER BY PATRON.PAT_FNAME, PATRON.PAT_LNAME, AUTHOR_NAME;
*/
