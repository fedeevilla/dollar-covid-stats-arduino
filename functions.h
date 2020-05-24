String getDolar()
{

  String dolar = "";
  HTTPClient http;

  http.begin("http://api-contenidos.lanacion.com.ar/json/V3/economia/cotizacionblue/DBLUE");

  int httpCode = http.GET();

  if (httpCode > 0)
  {
    String payload = http.getString();
    DynamicJsonDocument doc(1024);
    deserializeJson(doc, payload);
    String venta = doc["venta"];
    String compra = doc["compra"];
    String variacion = doc["variacion"];
    String fecha = doc["fecha"];
    fecha.replace('T', ' ');
    dolar = "$" + compra + " - $" + venta + "\n" + "(" + variacion + "%)" + "\n" + fecha.substring(0, 16);
  }

  http.end();
  return dolar;
}

String getCovid()
{
  String covid = "";
  HTTPClient http;

  http.begin("http://coronavirus-19-api.herokuapp.com/countries/argentina");
  int httpCode = http.GET();

  if (httpCode > 0)
  {
    String payload = http.getString();
    DynamicJsonDocument doc(1024);
    deserializeJson(doc, payload);
    String cases = doc["cases"];
    String deaths = doc["deaths"];
    String todayCases = doc["todayCases"];
    String todayDeaths = doc["todayDeaths"];
    covid = "Total: " + cases + "\n" + "Casos nuevos: " + todayCases + "\n" + "Muertes: " + deaths + " (+" + todayDeaths + ")";
  }

  http.end();
  return covid;
}
