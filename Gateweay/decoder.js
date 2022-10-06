function Decoder(bytes, port) {
  var temp = (bytes[0] << 8) | bytes[1];
  var hum = (bytes[2] << 8) | bytes[3];
  var p = (bytes[4] << 8) | bytes[5];
  var co2 = (bytes[6] << 8) | bytes[7];
  var tvoc = (bytes[8] << 8) | bytes[9];
  var o3 = (bytes[10] << 8) | bytes[11];
  var pm2 = (bytes[12] << 8) | bytes[13];
  var pm10 = (bytes[14] << 8) | bytes[15];
  
  return {
    temperature: temp/100,
    humidity: hum/100,
    pressure: p/10,
    co2: co2/100,
    tvoc: tvoc/100,
    o3: o3/100,
    pm2_5: pm2/100,
    pm10: pm10
  };
}
