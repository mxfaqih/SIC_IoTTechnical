from flask import Flask, request, jsonify

app = Flask(__name__)

@app.route('/api/ldr', methods=['POST'])
def ldr_data():
    data = request.get_json()
    ldr_value = data['ldr_value']
    
    if ldr_value < 1000:
        brightness = "Gelap"
    elif ldr_value < 2000:
        brightness = "Redup"
    else:
        brightness = "Terang"
    
    response = {"status": "success", "brightness": brightness}
    return jsonify(response)

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=8000, debug=True)
