




constexpr const int MAX_ABONENT_NUMBER_IN_CONF = 10; // TODO :: find wherever this value was set up
constexpr const int DEGRADATOR_STEPS_COUNT = MAX_ABONENT_NUMBER_IN_CONF;

template <typename T, typename FT>
struct degradator_setup_row {
	T spk_vol;
	FT mic_vol;
	T eq[5];
};

constexpr const degradator_setup_row<s16,float> degradator_setup_row_db[DEGRADATOR_STEPS_COUNT]{
	{-15, 0.f, {-12, 0, 0,  0,  1}},
	{-15, 0.f, {-12, 0, 4, -6, -8}},
	{-15, 0.f, {-12, 0, 4, -6, -8}},
	{-16, 0.f, {-12, 0, 4, -6, -9}},
	{-16, 0.f, {-12, 0, 4, -6, -9}},
	{-17, 0.f, {-12, 0, 4, -6, -10}},
	{-17, 0.f, {-12, 0, 4, -6, -10}},
	{-18, 0.0f, {-12, 0, 4, -6, -12}},
	{-18, 0.0f, {-12, 0, 4, -6, -12}},
	{-18, 0.0f, {-12, 0, 4, -6, -12}},
};

constexpr const u16 degradator_eq_setup[5] = {
	0x2400 | (0b11 << 5) | (0 << 8),
	0x2600 | (0b11 << 5) | (1 << 8),
	0x2800 | (0b01 << 5) | (1 << 8),
	0x2A00 | (0b11 << 5) | (1 << 8),
	0x2C00 | (0b01 << 5) | (0)
};

template <int size>
struct degradator_setup_data {
	
	constexpr degradator_setup_data() : raw()
	{
		for (int i = 0; i < size; i++) 
		{
			raw[i].spk_vol = ((u16)(degradator_setup_row_db[i].spk_vol + 57)) | 0x6C00;
			raw[i].mic_vol = ((u16)((degradator_setup_row_db[i].mic_vol + 12.f)/0.75)) | 0x5A00;
			for (int j = 0; j < 5; j++) 
			{
				raw[i].eq[j] = ((u16)(24 - (degradator_setup_row_db[i].eq[j] + 12))) | degradator_eq_setup[j];
			}
		}
	}
	
	degradator_setup_row<u16,u16> raw[size];


	degradator_setup_row<u16,u16> operator[](const int& index) const{
		return raw[index];
	};
};


constexpr const degradator_setup_data<DEGRADATOR_STEPS_COUNT> deg_set_dat;


//
// пример применения constexpr для вычисления табличных значений..
// задаём значения в ДБ, получаем команду для отправки в кодек
// во время компиляции
// восхитительно
//

