const element = document.getElementById('element-1');
function changeSize(size_number) {
    if (size_number) {
        element.style.width = '250px';
        element.style.height = '250px';
    }
    else if (!size_number) {
        element.style.width = '100px';
        element.style.height = '100px'; 
    }
}

async function changeColor() {
    try {
        const response = await fetch("http://localhost:8080/getRandomColors");
        if(!response.ok) {
            throw new Error(`Response status: ${response.status}`);
        }
        const json = await response.json();
        console.log(json);
        element.style.background = `#${json.hex}`;
    }
    catch (error) {
        console.error(error.message);
    }
}