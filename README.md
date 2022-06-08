# BigO-Calculator
.txt uzantılı dosyadan okunan C kodunun Big O notasyonuna göre zaman karmaşıklığını hesaplar.<br />
Calculates the time complexity of the C code read from the .txt file according to the Big O notation.
![alt text](data:image/png;base64,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)
