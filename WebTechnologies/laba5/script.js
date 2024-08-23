const form = document.getElementById('form');
const username = document.getElementById('username');
const email = document.getElementById('email');
const surname = document.getElementById('surname');
const patronymic = document.getElementById('patronymic');
const selectOption = document.getElementById('hobby-select');
const selectotherOption = document.getElementById('hobby-select-other');
const phoneadd = document.getElementById('input-block-phone');

// Добавление обработчика событий к кнопке закрытия модального окна
document.querySelector('.close-button').addEventListener('click', function () {
    document.querySelector('.overlay').classList.toggle('show');
});

// Добавление номера телефона
function createPhoneInput() {
    return function () {
        const input = document.createElement('input');
        input.type = "phone";
        input.name = `Дополнительный номер телефона`;
        input.pattern = "^\\+7\\d{10}$";
        phoneadd.appendChild(input);
    };
}

// Создание дополнительного телефона
const addPhoneInput = createPhoneInput();

document.querySelector('#add-phone').addEventListener('click', addPhoneInput);

// Обработка отправки формы
form.addEventListener('submit', e => {
    // Предотвращение отправки формы
    e.preventDefault();

    // Проверка валидности формы
    if (validateForm()) {
        // Отображение модального окна
        document.querySelector('.overlay').classList.toggle('show');

        // Создание блока c данными
        const result = document.getElementById('notification');
        const formData = new FormData(form);
        const data = {};

        // Сбор данных формы
        formData.forEach((value, key) => {
            data[key] = value;
        })

        result.innerHTML = '<h1 style="color: #09c375"> Ваша анкета сохранена</h1>';

        // Вывод каждого поля формы в блок уведомления
        Object.keys(data).forEach( key => {
            if (data[key] !== "") {
                const row = document.createElement('p');
                row.textContent = `${key}: ${data[key]}`;
                result.appendChild(row);
            }
        })
    }
});

// Добавление блока
selectOption.addEventListener('change', function () {
    if (selectOption.value === 'Другое') {
        selectotherOption.style.display = 'block'; // Добавление блока
    } else {
        selectotherOption.value = "";
        selectotherOption.style.display = 'none'; // Скрытие блока
    }
});

// Ошибки
const setError = (element, message) => {
    const inputControl = element.parentElement;
    const errorDisplay = inputControl.querySelector('.error');

    errorDisplay.innerText = message;
    inputControl.classList.add('error'); // Вывод ошибки
    inputControl.classList.remove('success'); // Все хорошо
};

// Проверка
const setSuccess = element => {
    const inputControl = element.parentElement;
    const errorDisplay = inputControl.querySelector('.error');

    errorDisplay.innerText = "";
    inputControl.classList.add('success'); // Все хорошо
    inputControl.classList.remove('error'); // Вывод ошибки
};

// Проверка почты
const isValidEmail = email => {
    const re = /^(([^<>()[\]\\.,;:\s@"]+(\.[^<>()[\]\\.,;:\s@"]+)*)|(".+"))@((\[[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}])|(([a-zA-Z\-0-9]+\.)+[a-zA-Z]{2,}))$/;
    return re.test(String(email).toLowerCase());
}

const validateForm = () => {
    const usernameValue = username.value.trim();
    const emailValue = email.value.trim();
    const surnameValue = surname.value.trim();
    const patronymicValue = patronymic.value.trim();

    let isValid = true;

    if (surnameValue === "") {
        setError(surnameValue, "Введите вашу фамилию!");
        isValid = false;
    } else { setSuccess(surname); }

    if (usernameValue === "") {
        setError(username, "Введите ваше имя!");
        isValid = false;
    } else { setSuccess(username); }

    if (patronymicValue === "") {
        setError(patronymic, "Введите ваше отчество!");
        isValid = false;
    } else { setSuccess(patronymic); }

    if (emailValue === "") {
        setError(email, "Введите ваш E-mail!");
        isValid = false;
    } else if (!isValidEmail(emailValue)){
        setError(email, "Введите корректный E-mail!");
        isValid = false;
    } else { setSuccess(email); }

    return isValid;
}