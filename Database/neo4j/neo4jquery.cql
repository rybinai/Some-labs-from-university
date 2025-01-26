// conect

http://localhost:7474/browser/

// Остановка (20)

UNWIND [
    "Университет", "Цирк", "Драмтеатр", "Железнодорожный вокзал", "Ленинская площадь", 
    "Горьковский парк", "Центральный рынок", "Городская библиотека", "Олимпийский стадион", "Городская больница", 
    "Школа №2", "Отделение почты", "Киноцентр", "Исторический музей", "Главный банк", 
    "Аптечный центр", "Центральный магазин", "Медицинская поликлиника", "Детский уголок", 
    "Фитнес-клуб"
] AS stopName
MERGE (s:Stop {name: stopName});

// Маршруты (5)

UNWIND [
    {number: 1, total_distance: 9.0},
    {number: 2, total_distance: 8.0},
    {number: 3, total_distance: 9.9},
    {number: 4, total_distance: 7.5},
    {number: 5, total_distance: 10.2}
] AS route
MERGE (r:Route {number: route.number, total_distance: route.total_distance});

// Маршрут 1
MERGE (r1:Route {number: 1, total_distance: 9.0});
MATCH (s1:Stop {name: "Университет"}), (s2:Stop {name: "Цирк"})
MERGE (s1)-[:NEXT {distance: 2.5, route: 1}]->(s2);
MATCH (s1:Stop {name: "Цирк"}), (s2:Stop {name: "Драмтеатр"})
MERGE (s1)-[:NEXT {distance: 1.8, route: 1}]->(s2);
MATCH (s1:Stop {name: "Драмтеатр"}), (s2:Stop {name: "Железнодорожный вокзал"})
MERGE (s1)-[:NEXT {distance: 3.2, route: 1}]->(s2);
MATCH (s1:Stop {name: "Железнодорожный вокзал"}), (s2:Stop {name: "Ленинская площадь"})
MERGE (s1)-[:NEXT {distance: 1.5, route: 1}]->(s2);

// Маршрут 2
MERGE (r2:Route {number: 2, total_distance: 8.0});
MATCH (s1:Stop {name: "Горьковский парк"}), (s2:Stop {name: "Центральный рынок"})
MERGE (s1)-[:NEXT {distance: 2.1, route: 2}]->(s2);
MATCH (s1:Stop {name: "Центральный рынок"}), (s2:Stop {name: "Драмтеатр"})
MERGE (s1)-[:NEXT {distance: 1.7, route: 2}]->(s2);
MATCH (s1:Stop {name: "Драмтеатр"}), (s2:Stop {name: "Городская библиотека"})
MERGE (s1)-[:NEXT {distance: 2.3, route: 2}]->(s2);
MATCH (s1:Stop {name: "Городская библиотека"}), (s2:Stop {name: "Олимпийский стадион"})
MERGE (s1)-[:NEXT {distance: 1.9, route: 2}]->(s2);

// Маршрут 3
MERGE (r3:Route {number: 3, total_distance: 9.9});
MATCH (s1:Stop {name: "Городская больница"}), (s2:Stop {name: "Школа №2"})
MERGE (s1)-[:NEXT {distance: 2.2, route: 3}]->(s2);
MATCH (s1:Stop {name: "Школа №2"}), (s2:Stop {name: "Отделение почты"})
MERGE (s1)-[:NEXT {distance: 1.6, route: 3}]->(s2);
MATCH (s1:Stop {name: "Отделение почты"}), (s2:Stop {name: "Драмтеатр"})
MERGE (s1)-[:NEXT {distance: 2.8, route: 3}]->(s2);
MATCH (s1:Stop {name: "Драмтеатр"}), (s2:Stop {name: "Киноцентр"})
MERGE (s1)-[:NEXT {distance: 1.4, route: 3}]->(s2);
MATCH (s1:Stop {name: "Киноцентр"}), (s2:Stop {name: "Исторический музей"})
MERGE (s1)-[:NEXT {distance: 1.9, route: 3}]->(s2);

// Маршрут 4
MERGE (r4:Route {number: 4, total_distance: 7.5});
MATCH (s1:Stop {name: "Главный банк"}), (s2:Stop {name: "Аптечный центр"})
MERGE (s1)-[:NEXT {distance: 1.5, route: 4}]->(s2);
MATCH (s1:Stop {name: "Аптечный центр"}), (s2:Stop {name: "Центральный магазин"})
MERGE (s1)-[:NEXT {distance: 2.0, route: 4}]->(s2);
MATCH (s1:Stop {name: "Центральный магазин"}), (s2:Stop {name: "Медицинская поликлиника"})
MERGE (s1)-[:NEXT {distance: 1.8, route: 4}]->(s2);
MATCH (s1:Stop {name: "Медицинская поликлиника"}), (s2:Stop {name: "Детский уголок"})
MERGE (s1)-[:NEXT {distance: 2.2, route: 4}]->(s2);

// Маршрут 5
MERGE (r5:Route {number: 5, total_distance: 10.2});
MATCH (s1:Stop {name: "Фитнес-клуб"}), (s2:Stop {name: "Олимпийский стадион"})
MERGE (s1)-[:NEXT {distance: 2.4, route: 5}]->(s2);
MATCH (s1:Stop {name: "Олимпийский стадион"}), (s2:Stop {name: "Школа №2"})
MERGE (s1)-[:NEXT {distance: 2.1, route: 5}]->(s2);
MATCH (s1:Stop {name: "Школа №2"}), (s2:Stop {name: "Университет"})
MERGE (s1)-[:NEXT {distance: 3.2, route: 5}]->(s2);

// Организации (20)

UNWIND [
    {name: "Университет технологий и дизайна", type: "EDUCATION", nearest_stop: "Университет"},
    {name: "ТЦ 'Мега'", type: "SHOP", nearest_stop: "Цирк"},
    {name: "Городская больница №1", type: "HEALTHCARE", nearest_stop: "Городская больница"},
    {name: "Школа №15", type: "EDUCATION", nearest_stop: "Школа №2"},
    {name: "Супермаркет 'Пятёрочка'", type: "SHOP", nearest_stop: "Центральный рынок"},
    {name: "Кафе 'У Петровича'", type: "FOOD", nearest_stop: "Драмтеатр"},
    {name: "Книжный магазин 'Читай-город'", type: "SHOP", nearest_stop: "Городская библиотека"},
    {name: "Спортивная школа", type: "EDUCATION", nearest_stop: "Олимпийский стадион"},
    {name: "Аптека 'Здоровье'", type: "HEALTHCARE", nearest_stop: "Аптечный центр"},
    {name: "Банк ВТБ", type: "FINANCE", nearest_stop: "Главный банк"},
    {name: "Детский сад №8", type: "EDUCATION", nearest_stop: "Детский уголок"},
    {name: "Магазин 'Продукты'", type: "SHOP", nearest_stop: "Центральный магазин"},
    {name: "Поликлиника №3", type: "HEALTHCARE", nearest_stop: "Медицинская поликлиника"},
    {name: "Фитнес-центр Maximum", type: "SPORT", nearest_stop: "Фитнес-клуб"},
    {name: "Почта России", type: "SERVICE", nearest_stop: "Отделение почты"},
    {name: "Кинотеатр 'Космос'", type: "ENTERTAINMENT", nearest_stop: "Киноцентр"},
    {name: "Краеведческий музей", type: "CULTURE", nearest_stop: "Исторический музей"},
    {name: "Театр драмы", type: "CULTURE", nearest_stop: "Драмтеатр"},
    {name: "Центральный рынок", type: "SHOP", nearest_stop: "Центральный рынок"}
] AS org
MATCH (s:Stop {name: org.nearest_stop})
MERGE (o:Organization {name: org.name, type: org.type})
MERGE (o)-[:LOCATED_NEAR]->(s);

// Запрос 

match – ищет узлы и связи в графе
1. Получить последовательность остановок для заданного маршрута.

MATCH (s1:Stop)-[r:NEXT {route: 1}]->(s2:Stop)
RETURN s1.name AS FromStop, s2.name AS ToStop, r.distance AS Distance
ORDER BY r.distance;

2. Получить названия организаций, расположенных рядом с заданной остановкой.

MATCH (s:Stop {name: "Университет"})<-[:LOCATED_NEAR]-(o:Organization)
RETURN o.name AS OrganizationName, o.type AS OrganizationType;

3. Найти все названия остановок, на которых возможны пересадки на другой маршрут.

MATCH (s:Stop)-[r1:NEXT]->(), (s)-[r2:NEXT]->()
WHERE r1.route <> r2.route
RETURN DISTINCT s.name AS TransferStops;

4. Найти все названия остановок, на которых останавливается только один маршрут.

MATCH (s:Stop)-[r:NEXT]->()
WITH s, COUNT(DISTINCT r.route) AS RouteCount
WHERE RouteCount = 1
RETURN s.name AS SingleRouteStops;

5. Найти названия учебных организаций и названия остановок, около которых они расположены.

MATCH (o:Organization {type: "EDUCATION"})-[:LOCATED_NEAR]->(s:Stop)
RETURN o.name AS EducationalOrgName, s.name AS StopName;
	
6. Получить все маршруты от одной заданной остановки до другой заданной остановки.

6.1 Остановки лежат на одном маршруте.

MATCH (s1:Stop {name: "Университет"})-[r:NEXT]->(s2:Stop {name: "Цирк"})
RETURN r.route AS Route;

6.2 Остановки лежат на разных маршрутах.

MATCH p = (s1:Stop {name: "Университет"})-[:NEXT*]->(s2:Stop {name: "Городская библиотека"})
WITH [r IN relationships(p) | r.route] AS Routes
RETURN DISTINCT Routes AS RouteNumbers;

7. Получить минимальный по количеству остановок маршрут от одной заданной остановки до другой заданной остановки.

7.1 Остановки лежат на одном маршруте.

MATCH p=shortestPath((s1:Stop {name: "Университет"})-[:NEXT*]-(s2:Stop {name: "Цирк"}))
RETURN p, length(p) AS StopsCount;

7.2 Остановки лежат на разных маршрутах.

MATCH p=shortestPath((s1:Stop {name: "Университет"})-[:NEXT|LOCATED_NEAR*]-(s2:Stop {name: "Городская библиотека"}))
RETURN p, length(p) AS StopsCount;

8. Получить все маршруты, которые проходят через 3 заданные остановки.

MATCH (s1:Stop)-[r1:NEXT]->(s2:Stop)-[r2:NEXT]->(s3:Stop)	
WHERE s1.name = "Университет" AND s2.name = "Цирк" AND s3.name = "Драмтеатр"
RETURN DISTINCT r1.route AS Route;

9. Получить маршрут, который проходит рядом с максимальным количеством магазинов.

MATCH (o:Organization {type: "SHOP"})-[:LOCATED_NEAR]->(s:Stop)-[r:NEXT]->()
RETURN r.route AS Route, COUNT(o) AS ShopCount
ORDER BY ShopCount DESC	
LIMIT 1;s

10. Получить минимальный по расстоянию маршрут от одной заданной остановки до другой заданной остановки.

MATCH p=shortestPath((s1:Stop {name: "Университет"})-[:NEXT*1..5]-(s2:Stop {name: "Городская библиотека"}))
RETURN p, reduce(totalDistance = 0, r IN relationships(p) | totalDistance + r.distance) AS TotalDistance;


11. Найти названия организаций, расположенных рядом с третьей по счету остановкой от заданной остановки. 

MATCH (s:Stop {name: "Университет"})-[:NEXT*3]->(thirdStop:Stop)
MATCH (o:Organization)-[:LOCATED_NEAR]->(thirdStop)
RETURN thirdStop.name AS ThirdStopName, o.name AS OrganizationName;

12. Найти все маршруты, длина которых превышает 10 км.

MATCH (r:Route)
WHERE r.total_distance > 10
RETURN r.number AS LongRoutes, r.total_distance AS TotalDistance;
