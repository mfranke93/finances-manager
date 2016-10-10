CREATE TABLE Category (
    id          INTEGER     PRIMARY KEY AUTOINCREMENT,
    name        TEXT NOT NULL,
    UNIQUE (name)
);
CREATE TABLE Recipient (
    id          INTEGER     PRIMARY KEY AUTOINCREMENT,
    name        TEXT        NOT NULL,
    address     TEXT        NOT NULL DEFAULT "",
    online      INTEGER     NOT NULL DEFAULT 0      CHECK(online IN (0, 1)),
    UNIQUE(name, address)
);
CREATE TABLE Item (
    id          INTEGER     PRIMARY KEY AUTOINCREMENT,
    name        TEXT        NOT NULL,
    recid       INTEGER     NOT NULL    REFERENCES Recipient(id) ON DELETE RESTRICT,
    date        TEXT        NOT NULL,
    price       FLOAT       NOT NULL,
    catid       INTEGER     NOT NULL    REFERENCES Category(id) ON DELETE RESTRICT
);
CREATE VIEW Expenditures AS
    SELECT  Item.name as Item,
            Category.name as Category, 
            Item.date as Date, 
            Recipient.name as Recipient,
            printf("%7s", printf("%.2f", Item.price)) as Price 
    FROM Item 
    JOIN Category 
        ON Item.catid=Category.id
    JOIN Recipient
        ON Item.recid=Recipient.id
    ORDER BY Date ASC;
