import pynmea2


with open('gps_data3.txt',mode='r') as in_file, open('gps_output.txt', mode='w') as out_file:

    for line in in_file:
        try:
            msg = pynmea2.parse(line)
            if msg.sentence_type == 'GGA':
                latitude = msg.latitude
                longitude = msg.longitude
                altitude = msg.altitude
                print('latitude: {} {}, longutude: {} {}, altitude {} , timestamp: {}'.format(msg.latitude, msg.lat_dir,msg.longitude, msg.lon_dir, msg.altitude, msg.timestamp))
                out_file.write('latitude: {} {}, longutude: {} {}, altitude {} , timestamp: {} \n'.format(msg.latitude, msg.lat_dir,msg.longitude, msg.lon_dir, msg.altitude, msg.timestamp))
        except pynmea2.ParseError as e:
            print('Parse error: {}'.format(e))
            continue
