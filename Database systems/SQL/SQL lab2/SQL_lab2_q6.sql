SELECT CONCAT(AUTHOR.AU_FNAME, ' ', AUTHOR.AU_LNAME) AS AUTHOR_NAME,
       COUNT(WRITES.BOOK_NUM) AS BOOKS_WRITTEN
FROM AUTHOR
LEFT JOIN WRITES ON AUTHOR.AU_ID = WRITES.AU_ID
GROUP BY AUTHOR_NAME
ORDER BY BOOKS_WRITTEN;

